import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('statistiques/evolution.csv', sep=';')

print(df.head())

plt.figure(figsize=(10, 6))

plt.plot(df['temps'], df['lapins'], label='Lapins', color='blue', marker='o')
plt.plot(df['temps'], df['renards'], label='Renards', color='red', marker='x')

plt.title('Évolution des populations de Lapins et Renards au fil du temps')
plt.xlabel('Temps (itérations)')
plt.ylabel('Nombre d\'animaux')

plt.legend()

plt.grid(True)
plt.show()
