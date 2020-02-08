; ModuleID = 'BasicOperators.cpp'
source_filename = "BasicOperators.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @_Z3addRKdS0_(double* dereferenceable(8), double* dereferenceable(8)) #0 {
  %3 = alloca double*, align 8
  %4 = alloca double*, align 8
  store double* %0, double** %3, align 8
  store double* %1, double** %4, align 8
  %5 = load double*, double** %3, align 8
  %6 = load double, double* %5, align 8
  %7 = load double*, double** %4, align 8
  %8 = load double, double* %7, align 8
  %9 = fadd double %6, %8
  ret double %9
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @_Z5minusRKdS0_(double* dereferenceable(8), double* dereferenceable(8)) #0 {
  %3 = alloca double*, align 8
  %4 = alloca double*, align 8
  store double* %0, double** %3, align 8
  store double* %1, double** %4, align 8
  %5 = load double*, double** %3, align 8
  %6 = load double, double* %5, align 8
  %7 = load double*, double** %4, align 8
  %8 = load double, double* %7, align 8
  %9 = fsub double %6, %8
  ret double %9
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @_Z3mulRKdS0_(double* dereferenceable(8), double* dereferenceable(8)) #0 {
  %3 = alloca double*, align 8
  %4 = alloca double*, align 8
  store double* %0, double** %3, align 8
  store double* %1, double** %4, align 8
  %5 = load double*, double** %3, align 8
  %6 = load double, double* %5, align 8
  %7 = load double*, double** %4, align 8
  %8 = load double, double* %7, align 8
  %9 = fmul double %6, %8
  ret double %9
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @_Z3divRKdS0_(double* dereferenceable(8), double* dereferenceable(8)) #0 {
  %3 = alloca double*, align 8
  %4 = alloca double*, align 8
  store double* %0, double** %3, align 8
  store double* %1, double** %4, align 8
  %5 = load double*, double** %3, align 8
  %6 = load double, double* %5, align 8
  %7 = load double*, double** %4, align 8
  %8 = load double, double* %7, align 8
  %9 = fdiv double %6, %8
  ret double %9
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.1-+20191211102125+c1a0a213378-1~exp1~20191211212701.104 "}
