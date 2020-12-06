#include "headers/TeamState.h"

TeamState::TeamState(Game* game)
    :State(game)
{
    m_teams = {
        "serbia",
        "spain",
        "russia",
        "poland",
        "turkey",
        "france",
        "germany"
    };
    m_selected = m_teams.size() / 2;
    m_background.setTexture(p_game->textures()->get("menu"));
    m_loadingImg.setTexture(p_game->textures()->get("loading"));
    m_loadingImg.setOrigin(m_loadingImg.getGlobalBounds().width/2, m_loadingImg.getGlobalBounds().height/2);
    m_loadingImg.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT-300);


    m_loading = false;

    m_current.setPosition(WINDOW_WIDTH/2 - 75, WINDOW_HEIGHT-300);
    m_current.setScale(1.5, 1.5);
    m_currPos = m_current.getPosition();

    m_backText.setPosition(5, 10);

    m_left.setScale(0.8, 0.8);
    m_left.setPosition(m_currPos.x - 80, m_currPos.y+50);
    m_left.setColor(sf::Color(255, 255, 255, 128));

    m_right.setScale(0.8, 0.8);
    m_right.setPosition(m_currPos.x + 150, m_currPos.y+50);
    m_right.setColor(sf::Color(255, 255, 255, 100));

    setTeams();

    m_teamName = sf::Text(m_teams[m_selected], p_game->fonts()->get("menu_font2"), 25);
    m_teamName.setPosition((m_currPos.x + 75) - ((m_teams[m_selected].size()/2.0)*18), m_currPos.y + 150);

    m_message = sf::Text("select your team", p_game->fonts()->get("menu_font2"), 30);
    m_message.setPosition(m_currPos.x - 80, m_currPos.y - 50);

    m_waitmsg = sf::Text("waiting for the oponent", p_game->fonts()->get("menu_font2"), 20);
    m_waitmsg.setPosition(WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT - 200);

}
TeamState::~TeamState() {

}

void TeamState::update() {
    if (m_loading) {
        m_loadingImg.rotate(3);
    }
    if (m_client.wait()) {
      m_loading=false;
      p_game->changeState(new PlayState(p_game, m_teams[m_selected], m_teams[m_client.selected()], m_client.receive(), m_client.send(), m_client.ip(),m_client.turn()));
    }
    // std::cout << m_client.send() << " " << m_client.receive() << " " << m_client.selected() << std::endl;
}
void TeamState::render(sf::RenderWindow& window) {
    window.draw(m_background);
    if (m_loading) {
        window.draw(m_loadingImg);
        window.draw(m_waitmsg);
    } else {
        window.draw(m_current);
        window.draw(m_left);
        window.draw(m_right);
        window.draw(m_teamName);
        window.draw(m_message);
    }
    window.draw(m_backText);
}
void TeamState::keyboard(sf::Keyboard::Key& key) {

    if (key == sf::Keyboard::Key::D  || key == sf::Keyboard::Key::Right) {
        m_selected = (m_selected + 1) % m_teams.size();
    } else if (key == sf::Keyboard::Key::A  || key == sf::Keyboard::Key::Left) {
        m_selected = (m_selected == 0 ? m_teams.size()-1 : m_selected-1);
    } else if (key == sf::Keyboard::Key::Space) {
        // Uvodimo socket koji ce naci prazan port, i cuvamo port
        // void
        // socket.send(packet,ip,20000);

        // unsigned short port_send=-1,port;
        // int selected;
        // while (1) {
          // if (selector.wait(sf::milliseconds(1))) {
          //   if (socket.receive(packet,ip,port) == sf::UdpSocket::Done)
          //     if (packet >> port_send >> selected)
          //        break;
          // }
        // }

        // socket.unbind();

        // std::cout << port_receive << " " << port_send << std::endl;
        /*
        * Probati da se konektuje, tj. poveze sa mrezom.
        * Ako protivnickog igraca jos nema, ili sta vec onda ide ovaj kod:
        */
        m_client.send(m_selected);

        m_loading = true;
        return;
        // u suprotnom prelazi u PlayState, izmenicemo argumente da se posalje i
        // naziv protivnicke ekipe
        // p_game->changeState(new PlayState(p_game, m_teams[m_client.selected()], m_client.receive(), m_client.send()));
        return;// mora return da se ne bi izvrsilo ovo setTeams nakon promene
    } else if (key == sf::Keyboard::Key::BackSpace) {
        if (m_loading) {
            m_loading = false;
        } else {
            p_game->changeState(new MenuState(p_game));
            return;
        }
    }

    setTeams();

}
void TeamState::setTeams() {
    m_current.setTexture(p_game->textures()->get(m_teams[m_selected]));
    m_teamName.setString(m_teams[m_selected]);

    m_teamName.setPosition((m_currPos.x + 75) - ((m_teamName.getString().getSize()/2.0)*18), m_currPos.y + 150);

    int leftVal = m_selected == 0 ? m_teams.size() - 1 : m_selected - 1;
    int rightVal = m_selected == (int)m_teams.size()-1 ? 0 : m_selected + 1;

    m_left.setTexture(p_game->textures()->get(m_teams[leftVal]));
    m_right.setTexture(p_game->textures()->get(m_teams[rightVal]));
}
void TeamState::mouse(sf::Event::MouseButtonEvent& event) {

}
