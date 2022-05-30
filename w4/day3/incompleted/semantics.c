/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

Object* lookupObject(char *name) {
  // DONE
  Scope* scope = symtab->currentScope;
  Object* obj;
  while (scope)
  {
    obj = findObject(scope->objList, name);
    if(obj) return obj;
    scope = scope->outer;
  }
  obj = findObject(symtab->globalObjectList, name);
  if(obj) return obj;
  return NULL;
  
}

void checkFreshIdent(char *name) {
  // TODO
  Object* obj = findObject(symtab->currentScope->objList, name);
  if(obj) return error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
}

Object* checkDeclaredIdent(char* name) {
  // TODO
}

Object* checkDeclaredConstant(char* name) {
  // TODO
}

Object* checkDeclaredType(char* name) {
  // TODO
}

Object* checkDeclaredVariable(char* name) {
  // TODO
}

Object* checkDeclaredFunction(char* name) {
  // TODO
}

Object* checkDeclaredProcedure(char* name) {
  // TODO
}

Object* checkDeclaredLValueIdent(char* name) {
  // TODO
}

