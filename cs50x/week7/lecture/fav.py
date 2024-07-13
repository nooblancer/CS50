from cs50 import SQL
import csv

#open database
db = SQL("sqlite:///fav.db")

#prompt for fav
favorite = input("Favorite: ")

#search
rows = db.execute("SELECT COUNT(*) AS n FROM fav WHERE problem = ?", favorite)

#get first (and only) row
row = rows[0]

#print result
print(row['n'])
