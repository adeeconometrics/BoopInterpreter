- [x] Configure the build system
- [x] Declaration of Scanner
- [x] Definition of Scanner
- [x] Declaration of TokenType
- [x] Definition of TokenType
- [x] Declaration of Token
- [x] Definition of Token
- [x] Declaration of Types
- [x] Declaration of ErrorHandler
- [x] Definition of ErrorHandler
- [x] Declaration of FileReader
- [x] Definition of FileReader
- [x] Declaration of Stmt
- [x] Definition of Stmt
- [x] Declaration of Expr
- [x] Definition of Expr
- [ ] Declaration of Callable
- [ ] Definition of Callable
- [ ] Declaration of Class
- [ ] Definition of Class
- [ ] Declaration of Function
- [ ] Definition of Function
- [ ] Declaration of Instance 
- [ ] Definition of Instance
- [ ] Declaration of Parser
- [ ] Definition of Parser
- [ ] Declaration of Environment
- [ ] Definition of Environment 
- [ ] Declaration of Evaluator
- [ ] Definition of Evaluator
- [ ] Documentation
- [ ] PPT Presentation 

---

Important parts to implement
- [x] Main
- [x] ErrorHandler
- Scanner
    - [x] Scanner
    - [x] Token
    - [x] TokenType
- Parser
    - [x] Expr
    - [x] Stmt
    - [x] Parser
    - [x] Function
    - [x] Callable
    - [x] Class
    - [x] Instance 
- ASTPrinter

- Update scanner for MINUS_MINUS, PLUS_PLUS, QUESTION operators

---
Things to Improve
- [ ] replace `std::string` to `std::string_view` when applicable
- [ ] write a JIT compiler (LLVM backend) 

---
Problems to solve:
- [ ] Find out a way to conviniently parse `std::any`
    - attempt: use `any_cast<decltype(obj.type())>()` -- not effective as `obj.type()` returns `std::type_info`
    - attempt: use `any_cast<auto>()` -- not effective as the compiler cannot deduce types 
    - suggested: use `std::variant` and `std::visit`
        - cost: cognitive overhead to implement template constructs which might require another translation unit 

- [ ] Subtitute `Object literal` as `std::optional<std::variant<double, std::string>>`
    - alternative: use abstract base class and declare virtual methods 
- [ ] Visitor patter: a pain to implement with template constructs
    - alternative: use `std::variant` instead of visitors

--- 
Cpp17 features
- `std::hold_alternative`
- `std::variant_size_v`
- `std::in_place`
- `std::string::npos`
- `std::hash<T>`
- `std::enable_share_from_this<T>`