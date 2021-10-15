#include "Game.h"

Game::Game() : window_("Game", sf::Vector2u{960, 900}, 60), tickRate_(240.0f)
{
    frametime_ = 1.0f / tickRate_;
    state_ = GameState::splash;
    window_.toggleBorderless();

    splashImage_ = textureManager_.getResource("Splashdd");
    if (splashImage_ == nullptr)
    {
        std::__throw_runtime_error("Couldn't load Splash image");
    }

    splash_.setTexture(*splashImage_);
    float scalex = (float)window_.getView().getSize().x / (float)splashImage_->getSize().x;
    float scaley = (float)window_.getView().getSize().y / (float)splashImage_->getSize().y;

    splash_.scale(scalex, scaley);
}

Game::~Game()
{
}

void Game::update()
{
    if (elapsed_.asSeconds() >= frametime_)
    {
        handleInput();
        window_.update();
        object_.tick(elapsed_);
        animateShip_.tick(elapsed_);
        animateShip_.animateTick(elapsed_);
        elapsed_ = sf::seconds(0.0);
    }
}

void Game::render()
{
    window_.beginDraw();
    switch (state_)
    {
    case GameState::play:
    {

        for (auto a : object_.getDrawable())
        {
            window_.draw(*a);
        }
        window_.draw(animateShip_);
        break;
    }

    case GameState::splash:
    {
        window_.draw(splash_);
        break;
    }

    default:
        //none
        break;
    }

    window_.endDraw();
}

GameWindow *Game::getWindow()
{
    return &window_;
}

void Game::handleInput()
{

    switch (state_)
    {
    case GameState::play:
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            object_.move(Object::Direction::Up, elapsed_);
            animateShip_.inputMove(Ship::Direction::Up, elapsed_);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            object_.move(Object::Direction::Down, elapsed_);
            animateShip_.inputMove(Ship::Direction::Down, elapsed_);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            object_.move(Object::Direction::Left, elapsed_);
            animateShip_.inputMove(Ship::Direction::Left, elapsed_);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            object_.move(Object::Direction::Right, elapsed_);
            animateShip_.inputMove(Ship::Direction::Right, elapsed_);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::K) || sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            object_.shoot();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window_.close();
        }
        break;
    }

    case GameState::splash:
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            state_ = GameState::play;
            window_.toggleBorderless();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window_.close();
        }
    }

    default:
        //none
        break;
    }
}

sf::Time Game::getElapsed()
{
    return elapsed_;
}

void Game::restartClock()
{
    elapsed_ += clock_.restart();
}
