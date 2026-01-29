## CDSVReader 

### Purpose  
The CDSVReader is intended to parse through delimiter-separated value (DSV) data from a `CDataSource`. It parses line by line, separating it by row into individual vectors while also separating each row into cells within each vector. The CDSVReader class contains an implementation struct as well as the methods End and ReadRow, as described below. The reader handles cases of quotes within a cell, embedded delimiters and new lines, empty cells, and leading/trailing delimiters.

### Constructor
```cpp
CDSVReader(std::shared_ptr< CDataSource > src, char delimiter);
```
- Parameters:
    - `src`: shared pointer to CDataSource where data is read from
    - `delimiter`: character designated for separating values in the DSV

### Destructor
```cpp
~CDSVReader();
```

### Methods
#### 1. End
```cpp
bool End() const;
```
Behavior: returns boolean value of whether or not the end of the data source has been reached, and all rows have been read.

#### 2. ReadRow
```cpp
bool ReadRow(std::vector<std::string> &row);
```
Behavior:
- returns boolean value of whether or not the end of the row has been reached; false the source is empty.
- parameters: `row` is an empty vector, strings (separated by delimiter) from `src` are pushed to the vector. These strings individually represent cells of the DSV file. 
- two double quotes inside cells represent a single double quote `""`->`"`
- if within quotes, `\n` and `delimiter` characters are treated as normal chars within the cell
- a row with just the `\n` character becomes a vector of size 0 and ReadRow returns true.
- a completely empty source does not create a vector and ReadRow returns false.
- leading and trailing delimiters create empty cells.

### Example
```cpp
using std::cout;
using std::endl;

auto src = std::make_shared<CStringDataSource>("Item,Price,Quantity\nBanana,3.00,20\n");
CDSVReader reader(src, ',');

std::vector<std::string> row;

while (reader.ReadRow(row)){
    for (const auto &cell : row) std::cout<<cell<<" ";
    std::cout<<std::endl;   
}
```
**Output:**  
Item Price Quantity  
Banana 3.00 20