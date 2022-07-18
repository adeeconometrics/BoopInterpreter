#include "../include/Environment.h"
#include "../include/ErrorHandler.h"

#include <map>
#include <memory>
#include <stdexcept>
#include <string>


#define EXPECT_TRUE(x) __builtin_expect(static_cast<int64_t>(x), 1)
#define EXPECT_FALSE(x) __builtin_expect(static_cast<int64_t>(x), 0)

namespace boop {

namespace {
class UndefinedVarAccess : public std::exception {};
class UninitializedVarAccess : public std::exception {};
} // namespace

// Environment definitions
Environment::Environment(EnvironmentPtr parent_env)
    : m_parent_env(parent_env) {}

auto Environment::assign(size_t hashed_var_name, BoopObject object) -> bool {
  auto iter = objects.find(hashed_var_name);
  if (iter != objects.end()) {
    objects.insert_or_assign(hashed_var_name, object);
    return true;
  }
  if (EXPECT_TRUE(m_parent_env != nullptr))
    return m_parent_env->assign(hashed_var_name, std::move(object));

  throw UndefinedVarAccess();
}

auto Environment::define(size_t hashed_var_name, BoopObject object) -> void {
  m_objects.insert_or_assign(hashed_var_name, object);
}

auto Environment::get(size_t hashed_var_name) -> BoopObject {
  auto iter = objects.find(hashedVarName);
  if (EXPECT_TRUE(iter != objects.end())) {
    if (EXPECT_FALSE(std::holds_alternative<std::nullptr_t>(iter->second)))
      throw UninitializedVarAccess();
    return iter->second;
  }
  if (EXPECT_TRUE(parentEnviron != nullptr))
    return parentEnviron->get(hashedVarName);

  throw UndefinedVarAccess(); // throws only in the global env
}

auto Environment::get_parent_env() -> EnvironmentPtr { return m_parent_env; }

auto Environment::is_global() -> bool { return (m_parent_env == nullptr); }

// EnvironmentManagement definitions
EnvironmentManager::EnvironmentManager(ErrorHandler &reporter)
    : m_error_handler(reporter),
      m_current_env(std::make_shared<Environment>(nullptr)) {}

auto EnvironmentManager::assign(const Token &variable, BoopObject object)
    -> void {
  try {
    m_current_env->assign(hasher(variable.get_lexeme()), std::move(object));
  } catch (const UndefinedVarAccess &e) {
    throw report_runtime_error(m_error_handler, variable,
                               "Can't assign to an undefined variable.");
  }
}

auto EnvironmentManager::create_new_env(
    const std::string &caller = __builtin_FUNCTION()) -> void {
  m_current_env = std::make_shared<Environment>(m_current_env);
}

auto EnvironmentManager::discard_envs_till(
    const Environment::EnvironmentPtr &env_to_restore,
    const std::string &caller = __builtin_FUNCTION()) -> void {

  while (EXPECT_TRUE(!m_current_env->is_global() &&
                     m_current_env.get() != env_to_restore.get())) {
    m_current_env = m_current_env->get_parent_env();
  }
}

auto EnvironmentManager::define(const std::string &token_str, BoopObject object)
    -> void {
        m_current_env->define(hasher(token_str), std::move(object));
}

auto EnvironmentManager::define(const Token &var_token, BoopObject object)
    -> void {
        m_current_env->define(hasher(var_token.get_lexeme()), std::move(object));
}

auto EnvironmentManager::get(const Token &var_token) -> BoopObject{
  try {
    return m_current_env->get(hasher(var_token.get_lexeme()));
  } catch (const UndefinedVarAccess &e) {
    throw report_runtime_error(
        eReporter, var_token, "Attempted to access an undefined variable.");
  } catch (const UninitializedVarAccess &e) {
    throw report_runtime_error(
        eReporter, var_token, "Attempted to access an uninitialized variable.");
  }
}

// auto EnvironmentManager::get(const std::string &var_token) -> BoopObject {
    
// }

auto EnvironmentManager::get_current_env() -> Environment::EnvironmentPtr{
    return m_current_env;
}

auto EnvironmentManager::set_current_env(
    Environment::EnvironmentPtr new_current,
    const std::string &callee = __builtin_FUNCTION()) -> void{

    m_current_env = std::move(next_current);
}

} // namespace boop