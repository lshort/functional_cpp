/**   This module provides support for inlining function calls
      with Boost::optional.  
*/

#include <functional>
#include <boost/optional/optional.hpp>

namespace opt {
    template<int N, typename T, typename FcnType,
             typename param1, typename ...params>
    boost::optional<T> opt( FcnType l, param1 arg1, params... args )  {
        return ([l, args] (param1 arg) { return l(arg, args...) }  )(arg1);
    };

    template<typename T, typename FcnType,
             typename param1, typename ...params>
    boost::optional<T> opt( FcnType l, param1 arg1, params... args )  {
        return ([l, args] (param1 arg) { return l(arg, args...) }  )(arg1);
    };

    
    
    /*
template<typename T, typename Lambda, typename ...params>
    boost::optional<T> opt( Lambda l, params... args )  {
        return l(hack_pack(args...));
    }
    */



}
