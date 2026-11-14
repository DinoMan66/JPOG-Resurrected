# Permuter: TMath::SphereIntersection in Src\TKernelInterface\TMath.cpp

Started 2026-11-12 22:45, seed None, 30 rounds x 20 variants. Score: bytes without a counterpart in the original (0 = exact). An exact result is a candidate until a normal build round verifies it.

Start (unchanged file): score 20
- round   1: 20 variants, best of round 20, best so far 20
- round   2: 20 variants, best of round 20, best so far 20
- round   3: 20 variants, best of round 20, best so far 20
- round   4: 20 variants, best of round 20, best so far 20
- round   5: 20 variants, best of round 20, best so far 20
- round   6: 20 variants, best of round 20, best so far 20
- round   7: 20 variants, best of round 20, best so far 20
- round   8: 20 variants, best of round 20, best so far 20
- round   9: 20 variants, best of round 20, best so far 20
- round  10: 20 variants, best of round 20, best so far 20
- round  11: 20 variants, best of round 20, best so far 20
- round  12: 20 variants, best of round 20, best so far 20
- round  13: 20 variants, best of round 20, best so far 20
- round  14: 20 variants, best of round 20, best so far 20
- round  15: 20 variants, best of round 20, best so far 20
- round  16: 20 variants, best of round 20, best so far 20
- round  17: 20 variants, best of round 20, best so far 20
- round  18: 20 variants, best of round 20, best so far 20
- round  19: 20 variants, best of round 20, best so far 20
- round  20: 20 variants, best of round 20, best so far 20
- round  21: 20 variants, best of round 20, best so far 20
- round  22: 20 variants, best of round 20, best so far 20
- round  23: 20 variants, best of round 20, best so far 20
- round  24: 20 variants, best of round 20, best so far 20
- round  25: 19 variants, best of round 20, best so far 20
- round  26: 19 variants, best of round 20, best so far 20
- round  27: 17 variants, best of round 20, best so far 20
- round  28: 15 variants, best of round 20, best so far 20
- round  29: 17 variants, best of round 20, best so far 20
- round  30: 19 variants, best of round 20, best so far 20

Tried 587 variants (0 did not compile). Best score 20.

### score 20: reorder declarations

```diff
--- current
+++ variant
@@ -1,6 +1,6 @@
 
     float penetration = 0.0f;
+    TVector3 delta;
     float radiusSum = radiusB + radiusA;
-    TVector3 delta;
     delta.Subtract(centreB, centreA);
     float radiusSumSq = radiusSum * radiusSum;
```

### score 20: swap operands; if (x)  <->  if (x != 0); swap operands

```diff
--- current
+++ variant
@@ -11,5 +11,5 @@
             *depth = penetration;
         }
-        if (offset != 0) {
+        if (offset) {
             if (depth == 0) {
                 penetration = radiusSum - (float)sqrt(distanceSq);
```

### score 20: swap operands; swap statements; swap statements

```diff
--- current
+++ variant
@@ -12,5 +12,5 @@
         }
         if (offset != 0) {
-            if (depth == 0) {
+            if (0 == depth) {
                 penetration = radiusSum - (float)sqrt(distanceSq);
             }
```

### score 20: swap operands

```diff
--- current
+++ variant
@@ -1,5 +1,5 @@
 
     float penetration = 0.0f;
-    float radiusSum = radiusB + radiusA;
+    float radiusSum = radiusA + radiusB;
     TVector3 delta;
     delta.Subtract(centreB, centreA);
```

### score 20: swap operands

```diff
--- current
+++ variant
@@ -11,5 +11,5 @@
             *depth = penetration;
         }
-        if (offset != 0) {
+        if (0 != offset) {
             if (depth == 0) {
                 penetration = radiusSum - (float)sqrt(distanceSq);
```

