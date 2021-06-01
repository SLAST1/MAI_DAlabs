N = 100000

with open("test.txt", "w") as f:
    f.write("abcgfhdeghheababctcehjtceghjtcehjdadeabcghheghhhheghhdeabcacbabchhjdetcehj\n")
    for i in range(N):
        f.write("abc\n")
        f.write("de\n")
        f.write("ghhe\n")
        f.write("tcehj\n")
