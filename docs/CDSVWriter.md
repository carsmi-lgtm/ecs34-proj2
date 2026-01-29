## CDSVWriter 

### Purpose  
The CDSVWriter class parses through vectors which represent lines of a delimiter-separated values (DSV) file, and have elements which represent cells in the DSV. The class has a WriteRow method, which writes elements from a single vector into CDataSink, including the necessary delimiters between cells. The writer handles embedded quotes by doubling them, and handles embedded new lines and delimiters by wrapping the entire cell in quotes. 

### Constructor
```cpp
CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall)
```
- Parameters:
    - `sink`: shared pointer to CDataSink where data written to and stored
    - `delimiter`: character designated for separating values in the DSV (If the delimiter is `"`, it is converted to `,` at the point of construction.)
    - `quoteall`: boolean value representing whether or not all cells must be wrapped in quotes

### Destructor
```cpp
~CDSVWriter();
```

### Methods

#### 2. WriteRow
```cpp
bool WriteRow(const std::vector<std::string> &row);
```
Behavior:
- returns boolean value of whether or not row was successfully written.
- parameters: `row` is vector representing one row of the DSV, containing strings which each represent a cell within that row. The cells of one row are written to the `sink`.
- double quotes inside cells are escaped by doubling them `"`->`""`
- Elements of the vector `row` are accessed one-by-one and each represented by `Str`. Characters of the string are individually written to the DSink.
- Correctly writes quotes before and after each cell if all cells are intended to be quoted.
- Correctly writes the delimiter between each cell.
- Handles embedded newline character, embedded quotes, and embedded delimiters by wrapping the entire cell in quotes.
- Adds `\n` after each row is written, and writes `\n` for an empty row.

### Example
```cpp
using std::cout;
using std::endl;

auto sink = std::make_shared<CStringDataSink>();
CDSVWriter writer(sink, ',',false);

std::vector<std::string> row = {"Item","Price","Quantity"};
writer.WriteRow(row);

std::cout<<sink->String<<endl;

```
**Output:**  
"Item,Price,Quantity\n"