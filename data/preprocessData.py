import csv

keywordsSet = set()

with open('./rawdata/geo-table.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        if row[-1] != "Postal Code" and row[-1] != "DMA Region" and row[-2] == "US":
            if ',' in row[1]: continue
            keywordsSet.add(row[1])

with open('./keywordTable.txt', "w") as csv_file:
    csv_writer = csv.writer(csv_file, delimiter = ',', quotechar = '"', quoting = csv.QUOTE_MINIMAL)
    for k in keywordsSet:
        csv_writer.writerow([k])
