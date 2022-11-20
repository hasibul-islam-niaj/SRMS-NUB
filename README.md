# SRMS-NUB

### STRUCTURES
ResultGrade {
	name,
	minPoint,
	maxPoint
}

Program {
	code,
	name
}

Semester {
	name,
}

Course {
	code,
	name,
	credit,
	program
}

Student {
	id,
	name,
	program,
}

StudentCourses {
	Semester,
	Courses[]
}

Result {
	Semester,
	Course,
	Result
}
