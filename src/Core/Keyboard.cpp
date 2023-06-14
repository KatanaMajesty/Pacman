#include "pch.h"
#include "Keyboard.h"

bool Keyboard::KeyIsPressed(sf::Keyboard::Key key) const noexcept
{
    return m_keyStates[key];
}

std::optional<Keyboard::Event> Keyboard::ReadKey() noexcept
{
    if (m_keyBuffer.size() > 0u)
    {
        Keyboard::Event key = m_keyBuffer.front();
        m_keyBuffer.pop();
        return key;
    }
    return {};
}

bool Keyboard::KeyIsEmpty() const noexcept
{
    return m_keyBuffer.empty();
}

void Keyboard::FlushKey() noexcept
{
    m_keyBuffer = std::queue <Keyboard::Event>();
}

void Keyboard::OnKeyPressed(sf::Keyboard::Key key) noexcept
{
    m_keyStates[key] = true;
    m_keyBuffer.push(Keyboard::Event(Keyboard::Event::Type::PRESS, key));
    TrimBuffer();
}

void Keyboard::OnKeyReleased(sf::Keyboard::Key key) noexcept
{
    m_keyStates[key] = false;
    m_keyBuffer.push(Keyboard::Event(Keyboard::Event::Type::RELEASE, key));
    TrimBuffer();
}

void Keyboard::ClearState() noexcept
{
    m_keyStates.reset();
}

void Keyboard::TrimBuffer() noexcept
{
    while (m_keyBuffer.size() > m_bufferCount)
    {
        m_keyBuffer.pop();
    }
}