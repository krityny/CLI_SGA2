#!/bin/bash
echo "Monitoring system.log for errors. Press Ctrl+C to stop."
tail -f system.log 2>/dev/null | grep --line-buffered "ERROR" | tee -a Report.txt

