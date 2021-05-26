#include "doctest.h"
#include "BinaryTree.hpp"
#include <iostream>

using namespace ariel;
using namespace std;

//Custom class to test template BinaryTree<Car>
class Car
{
    string company;
    
    public:
        Car(string comp) : company(comp){}
        bool operator==(const Car &other) const {return this->company == other.company;}
        friend ostream &operator<<(ostream &out, const Car &other) {return out<<other.company;}
};

TEST_CASE("Binary tree building tests")
{
    BinaryTree<int> a;
    
    //Test adding without a root
    CHECK_THROWS(a.add_left(0,2));    
    CHECK_THROWS(a.add_right(0,2));

    //Test add_root
    CHECK_NOTHROW(a.add_root(0));
    for (auto num : a) {CHECK_EQ(num, 0);}

    //Test overriding root
    CHECK_NOTHROW(a.add_root(1));
    for (auto num : a) {CHECK_EQ(num, 1);}

    //Override root and test adding nodes
    CHECK_NOTHROW(a.add_root(0));
    CHECK_NOTHROW(a.add_left(0,1));
    CHECK_NOTHROW(a.add_right(0, 2));
    CHECK_NOTHROW(a.add_left(1,3).add_right(1,4));
    CHECK_NOTHROW(a.add_left(2,5).add_right(2,6));

    //Test adding nodes to non-existing nodes
    CHECK_THROWS(a.add_left(100,2));
    CHECK_THROWS(a.add_right(50,7));

    //Test that the nodes were added properly
    int expected_output[] = {3,1,4,0,5,2,6}; //Should be inorder
    int i = 0;
    for (auto num : a)
    {
        CHECK_EQ(num, expected_output[i++]);
    }
}

TEST_CASE("Inorder iterator test")
{
    //Test premitive variable - int
    BinaryTree<int> tree_int;

    CHECK_NOTHROW(tree_int.add_root(0).
                    add_left(0,1).
                    add_right(0, 2).
                    add_left(1,3).
                    add_right(1,4).
                    add_left(2,5).
                    add_right(2,6)); //Add nodes

    /*
    		______________	0_______________
	______	1_____			        ______	2_______
	3		     4		            5		       6
    */
    //Test inorder iterator works propely like the array:
    int expected_int_output[] = {3,1,4,0,5,2,6};
    int i = 0;
    for (auto it = tree_int.begin_inorder() ; it != tree_int.end_inorder() ; it++)
    {
        CHECK_EQ((*it), expected_int_output[i++]);
    }
    
    //Test class - string
    BinaryTree<string> tree_string;

    CHECK_NOTHROW(tree_string.add_root("Ancestor").
                    add_left("Ancestor","Father").
                    add_right("Ancestor", "Mother").
                    add_left("Father","Son").
                    add_right("Son","Grandson").
                    add_left("Mother","Daughter").
                    add_right("Daughter","Granddaughter"));//Add nodes
                    
    /*
    		______________	Ancestor_______________
	______Father			            __________Mother
  Son_______		                 Daughter____
		  Grandson		                        Granddaughter		
    */

    //Test inorder iterator works propely like the array:    
    string expected_string_output[] = {"Son","Grandson", "Father", "Ancestor", "Daughter", "Granddaughter", "Mother"};
    i = 0;

    for (auto it = tree_string.begin_inorder() ; it != tree_string.end_inorder() ; it++)
    {
        CHECK_EQ((*it), expected_string_output[i++]);
    }
	
    //Test custom class - Car
    BinaryTree<Car> tree_car;

    CHECK_NOTHROW(tree_car.add_root(Car("Volvo")).
                    add_left(Car("Volvo"),Car("Ferrari")).
                    add_left(Car("Ferrari"), Car("Honda")).
                    add_right(Car("Ferrari"),Car("Tesla")).
                    add_right(Car("Volvo"),Car("Kia")).
                    add_right(Car("Kia"),Car("Beatle")));//Add nodes

    /*
    		______________Volvo_______________
    _____Ferrari______			             Kia______
  Honda		        Tesla                           Beatle		
    */

    //Test inorder iterator works propely like the array:    
    Car expected_car_output1[] = {Car("Honda"),Car("Ferrari"),Car("Tesla"),
                                Car("Volvo"),Car("Kia"),Car("Beatle")};
    i = 0;

    for (auto it = tree_car.begin_inorder() ; it != tree_car.end_inorder() ; it++)
    {
        CHECK_EQ((*it), expected_car_output1[i++]);
    }

    //Check that iterator is updated after changes AND check prefix ++ operator:
    CHECK_NOTHROW(tree_car.add_root(Car("Bike")));
    CHECK_NOTHROW(tree_car.add_right(Car("Bike"), Car("Jaguar")));

    /*
    		______________Bike_______________
    _____Ferrari______			             Jaguar______
  Honda		        Tesla                           Beatle		
    */

    Car expected_car_output2[] = {Car("Honda"),Car("Ferrari"),Car("Tesla"),
                                Car("Bike"),Car("Jaguar"),Car("Beatle")};
    i = 0;

    for (auto it = tree_car.begin_inorder() ; it != tree_car.end_inorder() ; ++it)
    {
        CHECK_EQ((*it), expected_car_output2[i++]);
    }
}

TEST_CASE("Preorder iterator test")
{
    //Test premitive variable - int
    BinaryTree<int> tree_int;

    CHECK_NOTHROW(tree_int.add_root(0).
                    add_left(0,1).
                    add_right(0, 2).
                    add_left(1,3).
                    add_right(1,4).
                    add_left(2,5).
                    add_right(2,6));

    /*
    		______________	0_______________
	______	1_____			        ______	2_______
	3		     4		            5		       6
    */

    //Test inorder iterator works propely like the array:
    int expected_int_output[] = {0,1,3,4,2,5,6};
    int i = 0;
    for (auto it = tree_int.begin_preorder() ; it != tree_int.end_preorder() ; it++)
    {
        CHECK_EQ((*it), expected_int_output[i++]);
    }

    //Test class - string
    BinaryTree<string> tree_string;

    CHECK_NOTHROW(tree_string.add_root("Ancestor").
                    add_left("Ancestor","Father").
                    add_right("Ancestor", "Mother").
                    add_left("Father","Son").
                    add_right("Son","Grandson").
                    add_left("Mother","Daughter").
                    add_right("Daughter","Granddaughter"));

    /*
    		______________	Ancestor_______________
	______Father			            __________Mother
  Son_______		                 Daughter____
		  Grandson		                        Granddaughter		
    */

    //Test inorder iterator works propely like the array:    
    string expected_string_output[] = {"Ancestor","Father", "Son", "Grandson", "Mother", "Daughter", "Granddaughter"};
    i = 0;

    for (auto it = tree_string.begin_preorder() ; it != tree_string.end_preorder() ; it++)
    {
        CHECK_EQ((*it), expected_string_output[i++]);
    }

    //Test custom class - Car
    BinaryTree<Car> tree_car;

    CHECK_NOTHROW(tree_car.add_root(Car("Volvo")).
                    add_left(Car("Volvo"),Car("Ferrari")).
                    add_left(Car("Ferrari"), Car("Honda")).
                    add_right(Car("Ferrari"),Car("Tesla")).
                    add_right(Car("Volvo"),Car("Kia")).
                    add_right(Car("Kia"),Car("Beatle")));

    /*
    		______________Volvo_______________
    _____Ferrari______			             Kia______
  Honda		        Tesla                           Beatle		
    */

    //Test inorder iterator works propely like the array:    
    Car expected_car_output1[] = {Car("Volvo"),Car("Ferrari"),Car("Honda"),
                                Car("Tesla"),Car("Kia"),Car("Beatle")};
    i = 0;

    for (auto it = tree_car.begin_preorder() ; it != tree_car.end_preorder() ; it++)
    {
        CHECK_EQ((*it), expected_car_output1[i++]);
    }

    //Check that iterator is updated after changes AND check prefix ++ operator:
    CHECK_NOTHROW(tree_car.add_root(Car("Bike")));
    CHECK_NOTHROW(tree_car.add_right(Car("Bike"), Car("Jaguar")));

    /*
    		______________Bike_______________
    _____Ferrari______			             Jaguar______
  Honda		        Tesla                           Beatle		
    */

    Car expected_car_output2[] = {Car("Bike"),Car("Ferrari"),Car("Honda"),
                                Car("Tesla"),Car("Jaguar"),Car("Beatle")};
    i = 0;

    for (auto it = tree_car.begin_preorder() ; it != tree_car.end_preorder() ; ++it)
    {
        CHECK_EQ((*it), expected_car_output2[i++]);
    }
}

TEST_CASE("Postorder iterator test")
{
    //Test premitive variable - int
    BinaryTree<int> tree_int;

    CHECK_NOTHROW(tree_int.add_root(0).
                    add_left(0,1).
                    add_right(0, 2).
                    add_left(1,3).
                    add_right(1,4).
                    add_left(2,5).
                    add_right(2,6));

    /*
    		______________	0_______________
	______	1_____			        ______	2_______
	3		     4		            5		       6
    */

    //Test inorder iterator works propely like the array:    
    int expected_int_output[] = {3,4,1,5,6,2,0};
    int i = 0;
    for (auto it = tree_int.begin_postorder() ; it != tree_int.end_postorder() ; it++)
    {
        CHECK_EQ((*it), expected_int_output[i++]);
    }

    //Test class - string
    BinaryTree<string> tree_string;

    CHECK_NOTHROW(tree_string.add_root("Ancestor").
                    add_left("Ancestor","Father").
                    add_right("Ancestor", "Mother").
                    add_left("Father","Son").
                    add_right("Son","Grandson").
                    add_left("Mother","Daughter").
                    add_right("Daughter","Granddaughter"));

    /*
    		______________	Ancestor_______________
	______Father			            __________Mother
  Son_______		                 Daughter____
		  Grandson		                        Granddaughter		
    */

    //Test inorder iterator works propely like the array:    
    string expected_string_output[] = {"Grandson","Son", "Father", "Granddaughter", "Daughter", "Mother", "Ancestor"};
    i = 0;

    for (auto it = tree_string.begin_postorder() ; it != tree_string.end_postorder() ; it++)
    {
        CHECK_EQ((*it), expected_string_output[i++]);
    }

    //Test custom class - Car
    BinaryTree<Car> tree_car;

    CHECK_NOTHROW(tree_car.add_root(Car("Volvo")).
                    add_left(Car("Volvo"),Car("Ferrari")).
                    add_left(Car("Ferrari"), Car("Honda")).
                    add_right(Car("Ferrari"),Car("Tesla")).
                    add_right(Car("Volvo"),Car("Kia")).
                    add_right(Car("Kia"),Car("Beatle")));

    /*
    		______________Volvo_______________
    _____Ferrari______			             Kia______
  Honda		        Tesla                           Beatle		
    */

    //Test inorder iterator works propely like the array:    
    Car expected_car_output1[] = {Car("Honda"),Car("Tesla"),Car("Ferrari"),
                                Car("Beatle"),Car("Kia"),Car("Volvo")};
    i = 0;

    for (auto it = tree_car.begin_postorder() ; it != tree_car.end_postorder() ; it++)
    {
        CHECK_EQ((*it), expected_car_output1[i++]);
    }

    //Check that iterator is updated after changes AND check prefix ++ operator:
    CHECK_NOTHROW(tree_car.add_root(Car("Bike")));
    CHECK_NOTHROW(tree_car.add_right(Car("Bike"), Car("Jaguar")));

    /*
    		______________Bike_______________
    _____Ferrari______			             Jaguar______
  Honda		        Tesla                           Beatle		
    */

    Car expected_car_output2[] = {Car("Honda"),Car("Tesla"),Car("Ferrari"),
                                Car("Beatle"),Car("Jaguar"),Car("Bike")};
    i = 0;

    for (auto it = tree_car.begin_postorder() ; it != tree_car.end_postorder() ; ++it)
    {
        CHECK_EQ((*it), expected_car_output2[i++]);
    }
}
