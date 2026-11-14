# Permuter: TGUIWidget::SetSize in Src\TGuiInterface\TGUIWidget.cpp

Started 2026-11-13 16:26, seed None, 30 rounds x 20 variants. Score: bytes without a counterpart in the original (0 = exact). An exact result is a candidate until a normal build round verifies it.

Start (unchanged file): score 7
- round   1: 20 variants, best of round 7, best so far 7
- round   2: 5 variants, best of round 8, best so far 7
Round 3: no new rewrites left - stopped.

Tried 26 variants (0 did not compile). Best score 7.

### score 7: swap operands

```diff
--- current
+++ variant
@@ -1,4 +1,4 @@
 
-    if (m_eSizeModeHoriz != SIZE_MODE_0) {
+    if (SIZE_MODE_0 != m_eSizeModeHoriz) {
         if (m_eSizeModeVert != SIZE_MODE_0) {
             if (m_sWidth != width || m_sHeight != height) {
```

### score 7: swap operands

```diff
--- current
+++ variant
@@ -1,5 +1,5 @@
 
     if (m_eSizeModeHoriz != SIZE_MODE_0) {
-        if (m_eSizeModeVert != SIZE_MODE_0) {
+        if (SIZE_MODE_0 != m_eSizeModeVert) {
             if (m_sWidth != width || m_sHeight != height) {
                 m_bValidated = false;
```

### score 7: swap operands; swap operands

```diff
--- current
+++ variant
@@ -1,5 +1,5 @@
 
-    if (m_eSizeModeHoriz != SIZE_MODE_0) {
-        if (m_eSizeModeVert != SIZE_MODE_0) {
+    if (SIZE_MODE_0 != m_eSizeModeHoriz) {
+        if (SIZE_MODE_0 != m_eSizeModeVert) {
             if (m_sWidth != width || m_sHeight != height) {
                 m_bValidated = false;
```

### score 8: swap statements; swap operands; swap statements

```diff
--- current
+++ variant
@@ -2,5 +2,5 @@
     if (m_eSizeModeHoriz != SIZE_MODE_0) {
         if (m_eSizeModeVert != SIZE_MODE_0) {
-            if (m_sWidth != width || m_sHeight != height) {
+            if (width != m_sWidth || m_sHeight != height) {
                 m_bValidated = false;
             }
```

### score 8: swap operands

```diff
--- current
+++ variant
@@ -2,5 +2,5 @@
     if (m_eSizeModeHoriz != SIZE_MODE_0) {
         if (m_eSizeModeVert != SIZE_MODE_0) {
-            if (m_sWidth != width || m_sHeight != height) {
+            if (m_sWidth != width || height != m_sHeight) {
                 m_bValidated = false;
             }
```

