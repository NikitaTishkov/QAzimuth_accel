#include "higlighter.h"

Higlighter::Higlighter(QTextDocument *parent)
                     : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
}

void Higlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
         QRegExp expression(rule.pattern);
         int index = expression.indexIn(text);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = expression.indexIn(text, index + length);
         }
     }
}
