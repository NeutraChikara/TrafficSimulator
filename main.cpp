/*
 * GL06TimerFunc.cpp: Translation and Rotation
 * Transform primitives from their model spaces to world space (Model Transform).
 */


#include "Systems/System.h"
#include <iostream>


//int main(int argc, char **argv) {
//    System system;
//    system.SetRequiredComponents(1);
//    return 0;
//}


template <class Tup, class Func, std::size_t ...Is>
constexpr void static_for_impl(Tup&& t, Func &&f, std::index_sequence<Is...> )
{
    (f(std::integral_constant<std::size_t, Is>{}, std::get<Is>(t)),...);
}

template <class ... T, class Func >
constexpr void static_for(std::tuple<T...>&t, Func &&f)
{
    static_for_impl(t, std::forward<Func>(f), std::make_index_sequence<sizeof...(T)>{});
}

int main()
{
    auto t = std::make_tuple( 1, 22, 3, 4, 8 );

    std::size_t weighted = 0;
    static_for(t, [&] (auto i, auto w) { std::cout << "i: " << i << " w: " << w << std::endl; });

    return 0;
}