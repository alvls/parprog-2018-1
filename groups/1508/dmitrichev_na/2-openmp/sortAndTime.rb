ar = Array.new()
IO.foreach("time.txt") do |line|
	ar.push(line.to_f)
end
sum = 0.0
ar.map { |num| sum+=num }
puts (ar.length.to_s+"\n")
puts (sum / ar.length).to_f
fo = File.open("time.txt",'w')
ar.sort!
ar.map { |num| fo.puts (num.to_s+"\n") }