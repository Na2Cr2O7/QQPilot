import sqlite3

conn = sqlite3.connect('dataset.db')
cur = conn.cursor()
cur.execute("SELECT question, answer FROM g ORDER BY rowid")  # 保持顺序一致
rows = cur.fetchall()
conn.close()

questions = [row[0] for row in rows]
answers = [row[1] for row in rows]
question_sets = [set(q) for q in questions]