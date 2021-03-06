#ifndef RBX_GC_MANAGED_THREAD
#define RBX_GC_MANAGED_THREAD

#include "gc/slab.hpp"

namespace rubinius {
  class SharedState;
  class VM;

  class ManagedThread {
  public:
    enum Kind {
      eRuby, eSystem
    };

  private:
    SharedState& shared_;
    Roots roots_;
    Kind kind_;
    const char* name_;
    int thread_id_;

  protected:
    gc::Slab local_slab_;

  public:
    ManagedThread(SharedState& ss, Kind kind);

    Roots& roots() {
      return roots_;
    }

    gc::Slab& local_slab() {
      return local_slab_;
    }

    Kind kind() {
      return kind_;
    }

    VM* as_vm() {
      if(kind_ == eRuby) return reinterpret_cast<VM*>(this);
      return 0;
    }

    const char* name() {
      return name_;
    }

    void set_name(const char* name) {
      name_ = name;
    }

    int thread_id() {
      return thread_id_;
    }

  };
}

#endif
