# Permuter: PGUITableBox::EnsureVisibleImpl in Src\PGUICore\PGUITableBox.cpp

Started 2026-11-13 16:26, seed None, 30 rounds x 20 variants. Score: bytes without a counterpart in the original (0 = exact). An exact result is a candidate until a normal build round verifies it.

Start (unchanged file): score 11
- round   1: 3 variants, best of round 10, best so far 10
Round 2: no new rewrites left - stopped.

Tried 4 variants (0 did not compile). Best score 10.

### score 10: swap operands

```diff
--- current
+++ variant
@@ -5,5 +5,5 @@
     Toshi::TNodeList<PGUIRowData>::Iterator it(row);
     Toshi::TNodeList<PGUIRowData>::Iterator end(m_oRows.End());
-    for (; it != end; ++it) {
+    for (; end != it; ++it) {
         if (it.Get() == m_pFirstRow) {
             m_pFirstRow = row;
```

### score 11: swap operands; swap statements

```diff
--- current
+++ variant
@@ -3,7 +3,7 @@
         return;
     }
+    Toshi::TNodeList<PGUIRowData>::Iterator end(m_oRows.End());
     Toshi::TNodeList<PGUIRowData>::Iterator it(row);
-    Toshi::TNodeList<PGUIRowData>::Iterator end(m_oRows.End());
-    for (; it != end; ++it) {
+    for (; end != it; ++it) {
         if (it.Get() == m_pFirstRow) {
             m_pFirstRow = row;
```

### score 12: swap statements

```diff
--- current
+++ variant
@@ -3,6 +3,6 @@
         return;
     }
+    Toshi::TNodeList<PGUIRowData>::Iterator end(m_oRows.End());
     Toshi::TNodeList<PGUIRowData>::Iterator it(row);
-    Toshi::TNodeList<PGUIRowData>::Iterator end(m_oRows.End());
     for (; it != end; ++it) {
         if (it.Get() == m_pFirstRow) {
```

