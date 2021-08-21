#ifndef SHARE_GC_TEST_C1_TESTBARRIERSETC1_HPP
#define SHARE_GC_TEST_C1_TESTBARRIERSETC1_HPP

#include "c1/c1_CodeStubs.hpp"
#include "gc/shared/c1/cardTableBarrierSetC1.hpp"

class TestBarrierSetC1 : public CardTableBarrierSetC1 {
protected:
  virtual void store_at_resolved(LIRAccess& access, LIR_Opr value);
};

class TestStub : public CodeStub {
private:
  LIR_Opr _addr;
public:
  TestStub(LIR_Opr addr) : _addr(addr) {}

  virtual void emit_code(LIR_Assembler* ce);
  virtual void visit(LIR_OpVisitState* visitor) {
    visitor->do_call();
  }

#ifndef PRODUCT
  virtual void print_name(outputStream *out) const {
    out->print("TestStub");
  }
#endif // PRODUCT
};

#endif // SHARE_GC_TEST_C1_TESTBARRIERSETC1_HPP
