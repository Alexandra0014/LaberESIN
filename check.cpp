#include "laberint.hpp"
#include <esin/util>

using util::nat;
using namespace std;

namespace check {

  bool comprova_cami_minim(const posicio& ini,
			     const posicio& final,
			     const laberint& L,
			     const list<posicio>& cami_candidat)
    throw(error) {
    cout<<final.first;
    cout<<ini.first;
    cout<<L.num_columnes();
    cout<<cami_candidat.size();
    return false;
  }

  bool comprova_perfecte(const laberint& L) {
    //cout<<L.num_columnes();
    laberint ll = L;
    return true;
  }
};
