#include <cstdint>
#include <malloc.h>

/*
 * GL06TimerFunc.cpp: Translation and Rotation
 * Transform primitives from their model spaces to world space (Model Transform).
 */



#include "Systems/System.h"
#include "Systems/Render.h"
#include "Components/TestComponent1.h"
#include "Components/TestComponent2.h"
#include "Components/ComponentUtility.h"
#include <iostream>

int main() {
    System system;
    system.SetRequiredComponents<TestComponent1, TestComponent2>();

    std::cout << ComponentUtility<TestComponent1>::GetId() << std::endl;
    std::cout << ComponentUtility<TestComponent2>::GetId() << std::endl;
    std::cout << ComponentUtility<TestComponent1>::GetId() << std::endl;
    std::cout << ComponentUtility<TestComponent2>::GetId() << std::endl;
}


