ZKL/
├── src/                      # Source code
│   ├── frontend/             # Frontend components
│   │   ├── lexer.c           # Lexer implementation
│   │   ├── parser.c          # Parser implementation
│   │   ├── lexer.h           # Lexer header
│   │   ├── parser.h          # Parser header
│   │   ├── ast.c             # AST implementation
│   │   ├── ast.h             # AST header
│   │   └── validator.c       # Code validation (semantic analysis)
│   │
│   ├── ir/                   # Intermediate Representation components
│   │   ├── ir_generator.c    # IR generation
│   │   ├── ir_generator.h    # IR generator header
│   │   ├── optimizer.c       # Optimizations for IR
│   │   ├── optimizer.h       # Optimizer header
│   │   └── ir_structs.h      # IR data structures (e.g., DAG, constraints)
│   │
│   ├── backend/              # Backend components
│   │   ├── constraint_compiler.c # Constraint generation
│   │   ├── constraint_compiler.h
│   │   ├── proof_generator.c # Interface to ZKP library
│   │   ├── proof_generator.h
│   │   ├── verifier_generator.c # Verifier generation
│   │   └── verifier_generator.h
│   │
│   ├── main.c                # Main program entry point
│   └── utils/                # Utility functions
│       ├── file_io.c         # File reading/writing
│       ├── file_io.h
│       ├── error_handling.c  # Error handling
│       └── error_handling.h
│
├── include/                  # Header files (public)
│   ├── zkl.h                 # Main public API header
│
├── tests/                    # Unit tests
│   ├── test_lexer.c
│   ├── test_parser.c
│   ├── test_ir.c
│   └── test_backend.c
│
├── docs/                     # Documentation
│   └── design.md             # Design document for the project
│
├── Makefile                  # Build instructions
├── README.md                 # Project overview
└── examples/                 # Example input programs
    ├── example1.zkl
    └── example2.zkl
