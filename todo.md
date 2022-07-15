- [x] Configure the build system
- [x] Declaration of Scanner
- [x] Definition of Scanner
- [x] Declaration of TokenType
- [ ] Definition of TokenType
- [x] Declaration of Token
- [ ] Definition of Token
- [x] Declaration of Types
- [ ] Declaration of ErrorHandler
- [ ] Definition of ErrorHandler
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
- Main
- ErrorHandler
- Scanner
    - Scanner
    - Token
    - TokenType
- Parser
    - Expr
    - Stmt
    - Function
    - Callable
    - Class
    - Instance 


---
Problems to solve:
- [ ] Find out a way to conviniently parse `std::any`
    - attempt: use `any_cast<decltype(obj.type())>()` -- not effective as `obj.type()` returns `std::type_info`
    - attempt: use `any_cast<auto>()` -- not effective as the compiler cannot deduce types 
    - suggested: use `std::variant` and `std::visit`
        - cost: cognitive overhead to implement template constructs which might require another translation unit 

- [ ] Subtitute `Object literal` as `std::optional<std::variant<double, std::string>>`
    - alternative: use abstract base class and declare virtual methods 