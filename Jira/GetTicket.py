import re

def extract_ticket_id(commit_message):
    match = re.search(r'\[(\w+-\d+)\]', commit_message)
    if match:
        return match.group(0)  # Returns the full ticket ID like [ABC-123]
    return None

# Example usage
commit_messages = [
    "[SPIH-101] Added SPI initialization",
    "[XYZ-202] Fixed bug in SPI communication",
    "[ABC-456] Updated documentation",
    "Some other commit without a ticket"
]

for message in commit_messages:
    ticket_id = extract_ticket_id(message)
    if ticket_id:
        print(f"{ticket_id}")