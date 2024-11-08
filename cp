# Set the URL for the ZIP file
url <- "https://www150.statcan.gc.ca/n1/tbl/csv/17100009-eng.zip"

# Create temporary files for both the zip and the extracted content
temp_zip <- tempfile(fileext = ".zip")
temp_dir <- tempdir()

tryCatch({
  # Download the ZIP file
  download.file(
    url = url,
    destfile = temp_zip,
    mode = "wb",
    method = "auto"
  )
  
  # Unzip the file
  unzip(temp_zip, exdir = temp_dir)
  
  # Find the CSV file in the extracted contents
  csv_file <- list.files(temp_dir, pattern = "\\.csv$", full.names = TRUE)[1]
  
  # Read the data
  data <- read.csv(csv_file)
  
  # Process the data
  canada_data <- data[data$GEO == "Canada", c("REF_DATE", "VALUE")]
  canada_data <- canada_data[order(canada_data$REF_DATE), ]
  
  # Verify the date range
  print(paste("Date range:", min(data$REF_DATE), "to", max(data$REF_DATE)))
  
}, error = function(e) {
  print(paste("Error occurred:", e))
}, finally = {
  # Clean up temporary files
  if(file.exists(temp_zip)) file.remove(temp_zip)
})
