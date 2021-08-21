#ifndef SHARE_GC_TEST_TESTBARRIERSET_HPP
#define SHARE_GC_TEST_TESTBARRIERSET_HPP

#include "gc/shared/barrierSet.hpp"
#include "gc/shared/cardTable.hpp"
#include "gc/shared/cardTableBarrierSet.hpp"

class TestBarrierSet: public CardTableBarrierSet {
  friend class VMStructs;

public:
  TestBarrierSet(CardTable* card_table);

  template <DecoratorSet decorators, typename BarrierSetT = TestBarrierSet>
  class AccessBarrier: public CardTableBarrierSet::AccessBarrier<decorators, BarrierSetT> {};
};

template<>
struct BarrierSet::GetName<TestBarrierSet> {
  static const BarrierSet::Name value = BarrierSet::TestBarrierSet;
};

template<>
struct BarrierSet::GetType<BarrierSet::TestBarrierSet> {
  typedef ::TestBarrierSet type;
};

#endif // SHARE_GC_TEST_TESTBARRIERSET_HPP
