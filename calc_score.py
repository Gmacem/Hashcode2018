import subprocess

if __name__ == "__main__":
    max_scores = []
    with open("max_score.txt", "r") as fin:
        for filename in ["a_example.in", "b_should_be_easy.in", "c_no_hurry.in", "d_metropolis.in", "e_high_bonus.in"]:
            filename, score = fin.readline().split()
            score = int(score)
            cat = subprocess.Popen(('cat', "tests/" + filename), stdout=subprocess.PIPE)
            output = subprocess.check_output(("./solve"), stdin=cat.stdout).decode()
            cat.wait()
            print("Filename:", filename)
            print(output)
            max_scores.append(max(score, int(output.split()[-1])))
    print("New total score:", sum(max_scores))
    with open("max_score.txt", "w") as fout:
        for score, filename in zip(max_scores, ["a_example.in", "b_should_be_easy.in", "c_no_hurry.in", "d_metropolis.in", "e_high_bonus.in"]):
            fout.write("{} {}\n".format(filename, score))

        fout.write("Summarize: {}\n".format(sum(max_scores)))
            
