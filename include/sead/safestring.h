#pragma once

namespace sead {

template<typename T>
class SafeStringBase
{
public:
    SafeStringBase(const T* data) : data(data) { }
    virtual ~SafeStringBase() { }

    virtual sead::SafeStringBase<T>& operator=(const sead::SafeStringBase<T>&);
    virtual void assureTerminationImpl_();

    const T* data;      // 4
};

using SafeString = SafeStringBase<char>;

}
