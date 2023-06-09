#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>

struct Event { bool handled = false; };

class EventDispatcher
{
public:
	virtual ~EventDispatcher() = default;
	inline void dispatch(Event& e) const
	{
		invokeHandler(e);
	}
private:
	virtual void invokeHandler(Event& e) const = 0;
};

template<typename Receiver, typename EventType>
class EventHandler : public EventDispatcher
{
public:
	using HandlerFn = void(Receiver::*)(const EventType&);

	EventHandler(Receiver* receiver, HandlerFn handlerFn)
		: m_Receiver(receiver), m_HandlerFn(handlerFn) {}

	virtual void invokeHandler(Event& e) const override
	{
		(m_Receiver->*m_HandlerFn)(static_cast<const EventType&>(e));
	}

	bool operator==(const EventHandler<Receiver, EventType>& rhs) const
	{
		return (m_Receiver == rhs.m_Receiver)
			&& (m_HandlerFn == rhs.m_HandlerFn);
	}
	bool operator==(Receiver* rhs) const
	{
		return m_Receiver == rhs;
	}
private:
	Receiver* m_Receiver;
	HandlerFn m_HandlerFn;
};

class EventBus
{
public:
	using Dispatcher = std::unique_ptr<EventDispatcher>;
	using HandlerList = std::vector<Dispatcher>;

private:
	EventBus() = default;
public:
	EventBus(const EventBus&) = delete;
	EventBus& operator=(const EventBus&) = delete;

	inline static EventBus& Get() { static EventBus instance; return instance; }

	template<typename EventType>
	void publish(EventType&& e)
	{
		auto entry = m_Subscriptions.find(typeid(EventType));
		if (entry != m_Subscriptions.end())
		{
			for (const auto& handler : entry->second)
			{
				if (e.handled) return;
				handler->dispatch(e);
			}
		}
	}

	template<typename Receiver, typename EventType>
	void subscribe(Receiver* receiver, void(Receiver::* handlerFn)(const EventType&))
	{
		HandlerList& handlers = m_Subscriptions[typeid(EventType)];
		handlers.emplace_back(
			std::make_unique<EventHandler<Receiver, EventType>>(receiver, handlerFn)
		);
	}

	template<typename Receiver, typename EventType>
	void unsubscribe(Receiver* receiver, void(Receiver::* handlerFn)(const EventType&))
	{
		auto entry = m_Subscriptions.find(typeid(EventType));
		if (entry != m_Subscriptions.end())
		{
			const EventHandler<Receiver, EventType> tmp = { receiver, handlerFn };
			HandlerList& handlers = entry->second;
			handlers.erase(std::remove_if(
				handlers.begin(),
				handlers.end(),
				[&](const auto& handler)
				{
					using T = EventHandler<Receiver, EventType>;
					return *static_cast<T*>(handler.get()) == tmp;
				}
			), handlers.end());
		}
	}

	template<typename Receiver>
	void unsubscribeAll(Receiver* receiver)
	{
		for (auto& [_, handlers] : m_Subscriptions)
		{
			handlers.erase(std::remove_if(
				handlers.begin(),
				handlers.end(),
				[&](const auto& handler)
				{
					using T = EventHandler<Receiver, Event>;
					return *static_cast<T*>(handler.get()) == receiver;
				}
			), handlers.end());
		}
	}
private:
	std::unordered_map<std::type_index, HandlerList> m_Subscriptions;
};