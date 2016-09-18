<?php

/**
 * Class PropertiesValueBuilderFieldable
 */
class EntityToolboxInfoPropertiesBuilderFieldable extends EntityToolboxInfoPropertiesBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'required_properties' => array(
          'entity_id',
          'entity_revision_id',
          'entity_human_name',
          'bundle',
          'created',
          'updated',
          'author',
          'status',
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}

