#include "precompiled.hpp"
#include "c1/c1_LIRAssembler.hpp"
#include "c1/c1_MacroAssembler.hpp"
#include "gc/shared/c1/cardTableBarrierSetC1.hpp"
#include "gc/test/c1/testBarrierSetC1.hpp"
#include "utilities/macros.hpp"

#ifdef ASSERT
#define __ gen->lir(__FILE__, __LINE__)->
#else
#define __ gen->lir()->
#endif

void TestBarrierSetC1::store_at_resolved(LIRAccess& access, LIR_Opr value) {
  LIRGenerator* gen = access.gen();
  DecoratorSet decorators = access.decorators();
  bool patch = (decorators & C1_NEEDS_PATCHING) != 0;

#ifdef _LP64
  LIR_Opr addr_reg = FrameMap::as_long_opr(c_rarg0);
#else
  LIR_Opr addr_reg = FrameMap::as_opr(c_rarg0);
#endif
  LIR_Opr addr = access.resolved_addr();
  if (addr->is_register() || addr->is_constant())
    __ move(addr, addr_reg);
  else {
    assert(addr->is_address(), "unexpected opr");
    LIR_Opr tmp = gen->new_pointer_register();
    if (patch) {
      __ leal(addr, tmp, lir_patch_normal, access.patch_emit_info());
      access.clear_decorators(C1_NEEDS_PATCHING);
    } else 
      __ leal(addr, tmp);
    access.set_resolved_addr(
      LIR_OprFact::address(new LIR_Address(tmp, access.type())));
    __ move(tmp, addr_reg);
  }

  CodeStub* stub = new TestStub(addr_reg);

  __ jump(stub);
  __ branch_destination(stub->continuation());

  CardTableBarrierSetC1::store_at_resolved(access, value);
}

void TestStub::emit_code(LIR_Assembler* ce) {
  ce->masm()->bind(*this->entry());

  //ce->masm()->call_VM_leaf(CAST_FROM_FN_PTR(address,
  //				   TestRuntime::some_function));

  ce->masm()->jmp(*this->continuation());
}