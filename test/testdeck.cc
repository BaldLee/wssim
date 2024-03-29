#include "utils/deck.hh"

using namespace wssim;

void test0() {
    std::cout << "test0" << std::endl;
    deck d;
    d.push_top(card(0, card::CHAR, 0));
    d.push_top(card(1, card::CHAR, 0));
    d.push_top(card(2, card::CHAR, 0));
    d.push_top(card(0, card::CLIMAX, 0));
    d.push_top(card(0, card::CLIMAX, 1));
    d.push_top(card(0, card::CLIMAX, 2));
    d.print();
    d.shuffle();
    d.print();
}

void test1() {
    std::cout << "test1" << std::endl;
    deck a;
    deck b;
    a.push_top(card(0, card::CHAR, 0));
    a.push_top(card(0, card::CHAR, 0));
    a.push_top(card(0, card::CHAR, 0));
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
    deck da;
    da.add_cards(1, card::CHAR, 0, 4);
    da.add_cards(0, card::CLIMAX, 1, 4);
    da.print();
    std::cout << da.to_str() << std::endl;
}

int main() {
    test0();
    test1();
    test2();
    return 0;
}