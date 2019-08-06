print("\n\n\n");

print("Please choose the log-level (1-4)\n\n"
      "1. EVENT\n"
      "2. WARN\n"
      "3. INFO\n"
      "4. DEBUG\n");

try:
    level = int(input())

    if( (level >= 1) and (level <= 4) ):
        with open("log_level", "w") as fp:
                fp.write(str(level))

    print("Log-Level changed successfully.\n\n")

except:
    print("Invalid value entered, exiting .. \n\n")
