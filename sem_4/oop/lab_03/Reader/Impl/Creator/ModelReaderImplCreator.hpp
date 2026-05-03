//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_MODELREADERIMPLCREATOR_HPP
#define LAB_03_MODELREADERIMPLCREATOR_HPP

template <typename BaseModelReaderImpl, Derivative<BaseModelReaderImpl> DerivedModelReaderImlp, typename ... Args>
    requires ConstructableWith<DerivedModelReaderImlp, Args ...>
template <typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args ...> && ...)
std::shared_ptr<BaseModelReaderImpl> ModelReaderImplCreator<BaseModelReaderImpl,
    DerivedModelReaderImlp, Args ...>::create(CallArgs && ... args)
{
    return std::make_shared<DerivedModelReaderImlp>(std::forward<CallArgs>(args)...);
}

#endif //LAB_03_MODELREADERIMPLCREATOR_HPP