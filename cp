# Download URL with date range
url <- "https://www150.statcan.gc.ca/t1/tbl1/en/dtl!downloadDbLoadingData-nonTraduit.action?pid=1710000901&latestN=0&startDate=2000-01-01&endDate=2024-07-01&csvLocale=en&selectedMembers=%5B%5B1%2C2%2C3%2C4%2C5%2C6%2C7%2C8%2C9%2C10%2C11%2C12%2C14%2C15%5D%5D&checkedLevels="

# Create a temporary file
temp_file <- tempfile(fileext = ".csv")

# Download the file
download.file(url = url,
             destfile = temp_file,
             mode = "wb",
             method = "auto")

# Read and filter data
data <- read.csv(temp_file)

# Filter for Canada and select only REF_DATE and VALUE
canada_data <- data[data$GEO == "Canada", c("REF_DATE", "VALUE")]

# Optional: Convert to data frame and arrange by date
canada_data <- as.data.frame(canada_data)
canada_data <- canada_data[order(canada_data$REF_DATE), ]

# Check the first few rows
head(canada_data)

# Check dimensions
cat("\nDimensions of filtered data:", dim(canada_data))

# Clean up temporary file
unlink(temp_file)
