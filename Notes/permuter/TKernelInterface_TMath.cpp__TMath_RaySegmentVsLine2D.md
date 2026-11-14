# Permuter: TMath::RaySegmentVsLine2D in Src\TKernelInterface\TMath.cpp

Started 2026-11-12 22:47, seed None, 30 rounds x 20 variants. Score: bytes without a counterpart in the original (0 = exact). An exact result is a candidate until a normal build round verifies it.

Start (unchanged file): score 24
- round   1: 18 variants, best of round 24, best so far 24
Round 2: no new rewrites left - stopped.

Tried 19 variants (0 did not compile). Best score 24.

### score 24: split declaration and assignment

```diff
--- current
+++ variant
@@ -2,5 +2,6 @@
     float determinant = lineDirection.y * rayDirection.x - lineDirection.x * rayDirection.y;
     if (determinant != 0.0f) {
-        TVector2 toLine = rayOrigin;
+        TVector2 toLine;
+        toLine = rayOrigin;
         toLine.Subtract(linePoint);
         float hit = (-toLine.x * lineDirection.y + lineDirection.x * toLine.y) / determinant;
```

### score 24: split declaration and assignment

```diff
--- current
+++ variant
@@ -1,4 +1,5 @@
 
-    float determinant = lineDirection.y * rayDirection.x - lineDirection.x * rayDirection.y;
+    float determinant;
+    determinant = lineDirection.y * rayDirection.x - lineDirection.x * rayDirection.y;
     if (determinant != 0.0f) {
         TVector2 toLine = rayOrigin;
```

### score 24: split declaration and assignment

```diff
--- current
+++ variant
@@ -4,5 +4,6 @@
         TVector2 toLine = rayOrigin;
         toLine.Subtract(linePoint);
-        float hit = (-toLine.x * lineDirection.y + lineDirection.x * toLine.y) / determinant;
+        float hit;
+        hit = (-toLine.x * lineDirection.y + lineDirection.x * toLine.y) / determinant;
         if (hit < t && 0.0f <= hit) {
             t = hit;
```

### score 24: split declaration and assignment; split declaration and assignment

```diff
--- current
+++ variant
@@ -2,7 +2,9 @@
     float determinant = lineDirection.y * rayDirection.x - lineDirection.x * rayDirection.y;
     if (determinant != 0.0f) {
-        TVector2 toLine = rayOrigin;
+        TVector2 toLine;
+        toLine = rayOrigin;
         toLine.Subtract(linePoint);
-        float hit = (-toLine.x * lineDirection.y + lineDirection.x * toLine.y) / determinant;
+        float hit;
+        hit = (-toLine.x * lineDirection.y + lineDirection.x * toLine.y) / determinant;
         if (hit < t && 0.0f <= hit) {
             t = hit;
```

### score 24: split declaration and assignment; split declaration and assignment

```diff
--- current
+++ variant
@@ -1,8 +1,10 @@
 
-    float determinant = lineDirection.y * rayDirection.x - lineDirection.x * rayDirection.y;
+    float determinant;
+    determinant = lineDirection.y * rayDirection.x - lineDirection.x * rayDirection.y;
     if (determinant != 0.0f) {
         TVector2 toLine = rayOrigin;
         toLine.Subtract(linePoint);
-        float hit = (-toLine.x * lineDirection.y + lineDirection.x * toLine.y) / determinant;
+        float hit;
+        hit = (-toLine.x * lineDirection.y + lineDirection.x * toLine.y) / determinant;
         if (hit < t && 0.0f <= hit) {
             t = hit;
```

