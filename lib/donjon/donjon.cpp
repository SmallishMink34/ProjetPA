#include "donjon.hpp"
#include "tree.hpp"
#include <fstream>


donjon::donjon(int nbnoeuds, int seed = 1) : noeuds(nbnoeuds), max_noeuds(nbnoeuds), max_children(3), max_depth(10), seed(seed), specialRooms(3), remaining_count(nbnoeuds) {
        letter = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        dirrection = {"bas", "haut"};
        dirrectionCopy = dirrection;
        std::random_device rd;
        std::mt19937 g(rd());
        // std::shuffle(letter.begin(), letter.end(), g);
        // std::shuffle(dirrection.begin(), dirrection.end(), g);
        // std::shuffle(dirrectionCopy.begin(), dirrectionCopy.end(), g);
        initial_Node = nullptr;
        
    }

char donjon::addletter() {
    char a =  letter[0];
    letter.erase(letter.begin());
    return a;
}

Node* donjon::searchNode(int x, int y, Node* node) {
    if (node->getRoom().getX() == x && (node->getRoom().getY() == y  || node->getRoom().getY() == y-1)) {
        return node;
    }
    for (Node* child : node->getChildren()) {
        Node* result = searchNode(x, y, child);
        if (result != nullptr) {
            return result;
        }
    }
    
    return nullptr;
}

Node* donjon::create_tree(int node_count) {
    char root_value = addletter();
    Node* root = new Node(rooms(0, 0, 32, 32, 2, 2), root_value);
    initial_Node = root;
    add_children(root, true, true, 0);
    return root;
}

bool donjon::addCoords(std::pair<int, int> coords) {
    if (std::find(CoordUse.begin(), CoordUse.end(), coords) == CoordUse.end()) {
        CoordUse.push_back(coords);
        return true;
    }
    return false;
}

int donjon::minX() {
    return std::min_element(CoordUse.begin(), CoordUse.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) { return a.first < b.first; })->first;
}

int donjon::maxX() {
    return std::max_element(CoordUse.begin(), CoordUse.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) { return a.first < b.first; })->first;
}

int donjon::minY() {
    return std::min_element(CoordUse.begin(), CoordUse.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) { return a.second < b.second; })->second;
}

int donjon::maxY() {
    return std::max_element(CoordUse.begin(), CoordUse.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) { return a.second < b.second; })->second;
}

std::vector<std::pair<int, int>> donjon::checks_valids(rooms room) {
    std::vector<std::pair<int, int>> valid = room.coordsarround();
    for (const std::pair<int, int>& i : room.coordsarround()) {
        if (std::find(CoordUse.begin(), CoordUse.end(), i) != CoordUse.end()) {
            valid.erase(std::remove(valid.begin(), valid.end(), i), valid.end());
        }
    }
    return valid;
}

bool donjon::checkTallRoom(int x, int y, std::string dirr) {
    return (std::find(CoordUse.begin(), CoordUse.end(), std::make_pair(x, y + (dirr == "bas" ? 1 : -1))) == CoordUse.end());
}

void donjon::add_children(Node* node, bool CanBeTall = true, bool Continuer = true, int depth = 0) {
    if (!Continuer) {
        return;
    }
    Continuer = true;

    int num_children;
    if (remaining_count == max_noeuds) {
        num_children = std::min(remaining_count, std::rand() % 2 + 3);
    }
    else if (remaining_count >= 3) {
        if (CanBeTall) {
            num_children = std::min(remaining_count, std::rand() % 6 + 1);
        }
        else {
            num_children = 1;
        }
    }
    else {
        if (CanBeTall) {
            num_children = std::min(remaining_count, std::rand() % 5);
        }
        else {
            num_children = std::min(remaining_count, std::rand() % 2);
        }
    }

    if (num_children > 1 || remaining_count == max_noeuds) {
        int choix = std::rand() % 2;
        addCoords(std::make_pair(node->getRoom().getX(), node->getRoom().getY()));
        if (choix == 0 && checkTallRoom(node->getRoom().getX(), node->getRoom().getY(), dirrection[choix])) {
            node->getRoom().setTall(2);
            addCoords(std::make_pair(node->getRoom().getX(), node->getRoom().getY() + 1));
            CanBeTall = false;
        }
        else if (choix == 1 && checkTallRoom(node->getRoom().getX(), node->getRoom().getY(), dirrection[(choix) % 2])) {
            if (std::find(CoordUse.begin(), CoordUse.end(), std::make_pair(node->getRoom().getX(), node->getRoom().getY() - 1)) == CoordUse.end()) {
                node->getRoom().setTall(2);
                node->getRoom().setY(node->getRoom().getY()-1);
                addCoords(std::make_pair(node->getRoom().getX(), node->getRoom().getY()));
                CanBeTall = false;
            }
        }
        else {
            node->getRoom().setTall(1);
            num_children = 1;
            CanBeTall = true;
        }
    }
    else if (remaining_count != max_noeuds - 1) {
        node->getRoom().setTall(1);
        CanBeTall = true;
    }

    if (remaining_count <= 0) {
        Continuer = false;
    }

    num_children = std::min(remaining_count, static_cast<int>(checks_valids(node->getRoom()).size()));
    num_children = std::min(num_children, max_children);
    if (depth >= max_depth) {
        num_children = 0;
    }

    remaining_count -= num_children;

    if (remaining_count <= 0) {
        Continuer = false;
    }

    for (int i = 0; i < num_children; i++) {
        char child_value = addletter();
        std::vector<std::pair<int, int>> Checked = checks_valids(node->getRoom());
        if (!Checked.empty()) {
            std::pair<int, int> coords = Checked[std::rand() % Checked.size()];
            while (!addCoords(coords)) {
                coords = Checked[std::rand() % Checked.size()];
            }

            Node* child = new Node(rooms(coords.first, coords.second), child_value);
            node->addChild(child);
            add_children(child, CanBeTall, Continuer, depth + 1);
        }
        else {
            // insert a the first position the letter child_value;
            letter.insert(letter.begin(), child_value);
            remaining_count += 1;
        }
    }
}

void donjon::SearchCelibRooms(Node* node) {
    if (node != nullptr) {
        if (node->getChildren().empty() && node->getRoom().getTall() == 1) {
            celibNode.push_back(node);
        }
        else {
            for (Node* i : node->getChildren()) {
                SearchCelibRooms(i);
            }
        }
    }
}

void donjon::addSpecialRooms(Node* node) {
    for (int i = 0; i < specialRooms; i++) {
        if (!celibNode.empty()) {
            node = celibNode[std::rand() % celibNode.size()];
            node->getRoom().setType(2);
            celibNode.erase(std::remove(celibNode.begin(), celibNode.end(), node), celibNode.end());
        }
        else {
            break;
        }
    }
}

void donjon::save_rooms_to_file(Node* node) {
    std::ofstream file("map.txt");
    if (file.is_open()) {
        for (int y = minY(); y <= maxY(); y++) {
            for (int x = minX(); x <= maxX(); x++) {
                if (std::find(CoordUse.begin(), CoordUse.end(), std::make_pair(x, y)) != CoordUse.end()) {
                    Node* searchnode = searchNode(x, y, node);
                    std::cout << searchnode->getValue() << "  aaaaaaaaaaaaaaaaaaaaa" << std::endl;
                    file << searchnode->getValue();
                }
                else {
                    file << "#";
                }
            }
            file << "\n";
        }
        file.close();
        save_path_to_file(node);
    }
}

void donjon::parcours_iteratif_write(Node* node, std::ofstream& txt) {
    txt << node->getValue() << " ";
    for (Node* i : node->getChildren()) {
        txt << i->getValue();
    }
    txt << "\n";
    for (Node* i2 : node->getChildren()) {
        parcours_iteratif_write(i2, txt);
    }
}

void donjon::save_path_to_file(Node* node) {
    std::ofstream file("mapPath.txt");
    parcours_iteratif_write(node, file);
    file.close();
}

int donjon::WidthLoad(std::ifstream& file) {
    int maxChar = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (line.length() > maxChar) {
            maxChar = line.length();
        }
    }
    file.clear();
    file.seekg(0, std::ios::beg);
    return maxChar;
}

int donjon::HeightLoad(std::ifstream& file) {
    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        count++;
    }
    file.clear();
    file.seekg(0, std::ios::beg);
    return count;
}

std::pair<int, int> donjon::SearchFromOrigin(char letter, int x, int y) {
    int oldx = 0;
    int oldy = 0;
    std::ifstream file("map.txt");
    std::string line;
    while (std::getline(file, line)) {
        for (char c : line) {
            if (c == letter) {
                return std::make_pair(oldx - x, oldy - y);
            }
            oldx++;
        }
        oldy++;
        oldx = 0;
    }
    file.close();
    return std::make_pair(-1, -1);
}

void donjon::load_rooms_from_file() {
    std::ifstream file("map.txt");
    std::string line;
    std::pair<int, int> origin = SearchFromOrigin('A', 0, 0);
    for (std::string x; std::getline(file, x);) {
        for (char y : x) {
            if (y == 'F') {
                std::pair<int, int> coords = SearchFromOrigin(y, origin.first, origin.second);
                rooms room(coords.first, coords.second);
                Node* branche = new Node(room, y);
                initial_Node = branche;
            }
        }
    }
    file.close();
}

void donjon::drawDungeon(Node* node) {
    if (node != nullptr) {
        std::cout << node->getValue() << " " << node->getAllChildValues() << std::endl;
        for (Node* i : node->getChildren()) {
            drawDungeon(i);
        }
    }
}

// void donjon::draw_tree(Node* node, int x, int y, int level) {
//     if (node != nullptr) {
//         // Draw the current node
//         display.draw_circle(x, y, 15, BLACK);
//         display.draw_text(std::to_string(node->value), x, y, WHITE);

//         // Draw lines to the children
//         int num_children = node->children.size();
//         if (num_children > 0) {
//             int child_spacing = SCREEN_WIDTH / (num_children + 1);
//             for (int i = 0; i < num_children; i++) {
//                 int child_x = (i + 1) * child_spacing;
//                 int child_y = y + 100;
//                 display.draw_line(x, y + 20, child_x, child_y - 20, BLACK, 2);
//                 draw_tree(node->children[i], child_x, child_y, level + 1);
//             }
//         }
//     }
// }
