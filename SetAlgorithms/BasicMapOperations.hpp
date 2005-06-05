// Oliver Kullmann, 4.6.2005 (Swansea)

#ifndef BASICMAPOPERATIONS_098Uik

#define BASICMAPOPERATIONS_098Uik

#include <functional>
#include <cassert>

namespace OKlib {

  namespace SetAlgorithms {

    template <class Map>
    struct MapValue : std::unary_function<typename Map::key_type, typename Map::value_type::second_type> {
      MapValue(const Map& map) : map(map) {}
    private :
      typedef typename Map::key_type key_type;
      typedef typename Map::value_type::second_type value_type;
      typedef typename Map::const_iterator const_iterator;
    public :
      const value_type& operator() (const key_type& x) const {
        const_iterator i(map.find(x));
        assert(i != map.end());
        return i -> second;
      }
    private :
      const Map& map;
    };

    template <class Map>
    typename MapValue<Map>::result_type map_value(const Map& map, const typename MapValue<Map>::argument_type& x) {
      return MapValue<Map>(map)(x);
    }
  }

}

#endif
