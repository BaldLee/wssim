#include "utils/deck.hh"

using namespace wssim;

void test0() {
    std::cout << "test0" << std::endl;
    Deck d;
    d.push_top(Card(0, Card::CHAR, 0));
    d.push_top(Card(1, Card::CHAR, 0));
    d.push_top(Card(2, Card::CHAR, 0));
    d.push_top(Card(0, Card::CLIMAX, 0));
    d.push_top(Card(0, Card::CLIMAX, 1));
    d.push_top(Card(0, Card::CLIMAX, 2));
    d.print();
    d.shuffle();
    d.print();
}

void test1() {
    std::cout << "test1" << std::endl;
    Deck a;
    Deck b;
    a.push_top(Card(0, Card::CHAR, 0));
    a.push_top(Card(0, Card::CHAR, 0));
    a.push_top(Card(0, Card::CHAR, 0));
    std::cout << "a";
    a.print();
    b = std::move(a);
    std::cout << "a";
    a.print();
    std::cout << "b";
    b.print();
    a.clear();
    std::cout << "a";
    a.print();
    std::cout << "b";
    b.print();
}

void test2() {
    std::cout << "test2" << std::endl;
    Deck da;
    da.add_cards(1, Card::CHAR, 0, 4);
    da.add_cards(0, Card::CLIMAX, 1, 4);
    da.print();
    std::cout << da.to_str() << std::endl;
}

int main() {
    test0();
    test1();
    test2();
    return 0;
}