#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "ErrorHandler.h"
#include "Token.h"
#include "Types.h"

#include <cstddef>
#include <exception>
// #include <list>
#include <map>
#include <memory>
#include <optional>

namespace boop {

class Environment : public Uncopyable,
                    std::enable_share_from_this<Environment> {
public:
  using EnvironmentPtr = std::shared_ptr<Environment>;

private:
  std::map<size_t, BoopObject> m_objects;
  EnvironmentPtr m_parent_env{nullptr};

public:
  explicit Environment(EnvironmentPtr parent_env);

  auto assign(size_t hashed_var_name, BoopObject object) -> bool;
  auto define(size_t hashed_var_name, BoopObject object) -> void;
  auto get(size_t hashed_var_name) -> BoopObject;
  auto get_parent_env() -> EnvironmentPtr;

  auto is_global() -> bool;
};

class EnvironmentManager : public Uncopyable {
private:
  ErrorHandler &m_error_handler;
  Environment::EnvironmentPtr m_current_env;
  std::hash<std::string> m_hasher;

public:
  explicit EnvironmentManager(ErrorHandler &reporter);

  auto assign(const Token &variable, BoopObject object) -> void;
  auto create_new_env(const std::string &caller = __builtin_FUNCTION()) -> void;
  auto discard_envs_till(const Environment::EnvironmentPtr &env_to_restore,
                         const std::string &caller = __builtin_FUNCTION())
      -> void;

  auto define(const std::string &token_str, BoopObject object) -> void;
  auto define(const Token &var_token, BoopObject object) -> void;
  auto get(const Token &var_token) -> BoopObject;
//   auto get(const std::string &var_token) -> BoopObject;
  auto get_current_env() -> Environment::EnvironmentPtr;
  auto set_current_env(Environment::EnvironmentPtr new_current,
                       const std::string &callee = __builtin_FUNCTION())
      -> void;
};

} // namespace boop

#endif // __ENVIRONMENT_H__