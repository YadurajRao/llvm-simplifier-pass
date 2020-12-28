#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <vector>
#include <map>

#include "llvm/IR/Module.h"
#include "z3++.h"

class Program {
public:
  explicit Program(llvm::Module&);

  z3::expr GetVariableExpr(std::string);

private:
  z3::context context_;
  std::map<std::string, z3::expr> global_var_init_map_;
  std::map<std::string, z3::expr> variable_expr_map_;
  std::vector<z3::expr> inst_exprs_;
  std::vector<std::string> inst_lval_operands_;
  std::vector<std::string> thread_names_;
  std::vector<std::vector<std::vector<std::pair<int, int> > > > thread_graphs_;
  // std::map<std::string, z3::expr> m_inst_expr_map_;
  // std::map<std::string, std::string> m_inst_lval_operand_map_;

  void ParseGlobalVariables(llvm::Module&);
  void ParseThread(llvm::Function&);

  std::string ValueToVariable(const llvm::Value*, std::string scope);
  z3::expr ValueToExpr(const llvm::Value*, std::string scope);

  bool AddVariable(std::string name);
};

#endif
