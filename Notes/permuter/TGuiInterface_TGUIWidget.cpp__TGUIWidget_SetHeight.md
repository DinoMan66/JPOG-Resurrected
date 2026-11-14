# Permuter: TGUIWidget::SetHeight in Src\TGuiInterface\TGUIWidget.cpp

Started 2026-11-13 16:26, seed None, 30 rounds x 20 variants. Score: bytes without a counterpart in the original (0 = exact). An exact result is a candidate until a normal build round verifies it.

Start (unchanged file): score 6
- round   1: 3 variants, best of round 6, best so far 6
Round 2: no new rewrites left - stopped.

Tried 4 variants (0 did not compile). Best score 6.

### score 6: swap operands

```diff
--- current
+++ variant
@@ -1,4 +1,4 @@
 
-    if (m_eSizeModeVert != SIZE_MODE_0) {
+    if (SIZE_MODE_0 != m_eSizeModeVert) {
         if (m_sHeight != height) {
             m_bValidated = false;
```

### score 7: swap operands

```diff
--- current
+++ variant
@@ -1,5 +1,5 @@
 
     if (m_eSizeModeVert != SIZE_MODE_0) {
-        if (m_sHeight != height) {
+        if (height != m_sHeight) {
             m_bValidated = false;
         }
```

### score 7: swap operands; swap operands

```diff
--- current
+++ variant
@@ -1,5 +1,5 @@
 
-    if (m_eSizeModeVert != SIZE_MODE_0) {
-        if (m_sHeight != height) {
+    if (SIZE_MODE_0 != m_eSizeModeVert) {
+        if (height != m_sHeight) {
             m_bValidated = false;
         }
```

