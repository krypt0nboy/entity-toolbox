<?php

/**
 * Returns an entity type line from installed_entities.
 *
 * @param $entity_type
 *   The entity type.
 *
 * @return mixed
 */
function toolbox_load_entity_status($entity_type) {
  $query   = db_select('installed_entities', 'i')
	->fields('i', array())
	->condition('i.entity_type', $entity_type);
  $result  = $query->execute();
  $results = array();
  while ($record = $result->fetchAssoc()) {
	$results[] = $record;
  }

  return reset($results);
}