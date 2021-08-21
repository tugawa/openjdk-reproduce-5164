#include "precompiled.hpp"
#include "runtime/thread.hpp"
#include "gc/test/testBarrierSet.hpp"
#include "gc/shared/barrierSet.hpp"
#include "gc/shared/cardTableBarrierSetAssembler.hpp"
#ifdef COMPILER1
#include "gc/test/c1/testBarrierSetC1.hpp"
#endif
#ifdef COMPILER2
#include "gc/shared/c2/cardTableBarrierSetC2.hpp"
#endif

TestBarrierSet::TestBarrierSet(CardTable* card_table) : CardTableBarrierSet(
          make_barrier_set_assembler<CardTableBarrierSetAssembler>(),
          make_barrier_set_c1<TestBarrierSetC1>(),
          make_barrier_set_c2<CardTableBarrierSetC2>(),
          card_table,
          BarrierSet::FakeRtti(BarrierSet::TestBarrierSet)) {}
