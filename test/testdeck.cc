#include "utils/deck.hh"

using namespace wssim;

void test0() {
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
    std:: cout << "a";
    a.print();
    b = std::move(a);
    std:: cout << "a";
    a.print();
    std:: cout << "b";
    b.print();
    a.clear();
    std:: cout << "a";
    a.print();
    std:: cout << "b";
    b.print();
}

int main() {
    test0();
    test1();
    return 0;
}