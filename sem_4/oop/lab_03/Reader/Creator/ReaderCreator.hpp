//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_READERCREATOR_HPP
#define LAB_03_READERCREATOR_HPP

template <typename Reader, typename... Args> requires ConstructableWith<Reader, Args...>
template <typename... CallArgs> requires (IsSupportedArgs<CallArgs, Args...> && ...)
std::shared_ptr<Reader> ReaderCreator<Reader, Args...>::create(CallArgs &&... args)
{
    return std::make_shared<Reader>(std::forward<CallArgs>(args)...);
}


#endif //LAB_03_READERCREATOR_HPP