#pragma once
#include "SFML/Window.hpp"

#include <bitset>
#include <queue>
#include <optional>

class Keyboard
{
    friend class Window;
public:
    class Event
    {
    public:
        enum class Type
        {
            PRESS,
            RELEASE
        };
    public:
        Event(Type type, sf::Keyboard::Key code)
            : m_type(type)
            , m_code(code)
        {}

        inline bool isPressed() const noexcept { return m_type == Type::PRESS; }
        inline bool isReleased() const noexcept { return m_type == Type::RELEASE; }
        inline sf::Keyboard::Key GetCode() const noexcept { return m_code; }
    private:
        Type m_type;
        sf::Keyboard::Key m_code;
    };
public:
    Keyboard() = default;
    Keyboard(const Keyboard&) = delete;
    Keyboard& operator=(const Keyboard&) = delete;

    bool KeyIsPressed(sf::Keyboard::Key key) const noexcept;
    std::optional<Event> ReadKey() noexcept;
    bool KeyIsEmpty() const noexcept;
    void FlushKey() noexcept;
private:
    void OnKeyPressed(sf::Keyboard::Key key) noexcept;
    void OnKeyReleased(sf::Keyboard::Key key) noexcept;
    void ClearState() noexcept;
    void TrimBuffer() noexcept;
private:
    static constexpr unsigned int m_nKeys = 256u;
    static constexpr unsigned int m_bufferCount = 16u;
    std::bitset<m_nKeys> m_keyStates;
    std::queue<Event> m_keyBuffer;
};