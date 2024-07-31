# Creating Unit Testing and Integration testing with pytest for C/C++

#### Prerequisites
Before you begin, ensure you have the following tools installed:
- GCC (GNU Compiler Collection)
- Python (with pytest, pytest-cov, pytest-html, and coverage.py packages)
You can install the necessary Python packages using pip:

```bash
pip install pytest pytest-cov pytest-html coverage
```
Project Structure
```markdown
your_project/
│
├── module1.c
├── module1.h
├── module2.c
├── module2.h
└── binding.py
│
├── tests/
│   ├── test_module1.py
│   ├── test_module2.py
│   └── test_integration.py
│
├── run_tests.bat
└── pytest.ini
```

#### You can download the files from the repo and continue the steps with me 
#### You can also skip the guide and run the bat script, it will automate all the steps

-   Compile the C code to generate the shared Library
```bash
gcc -shared -o module1.so -fPIC module1.c
gcc -shared -o module2.so -fPIC module2.c
```

-   Run pytest and output reports to test_results folder
```bash
pytest --cov=your_module --cov-branch --cov-report=html:test_results/cov_report.html --junitxml=test_results/report.xml --html=test_results/report.html
```
