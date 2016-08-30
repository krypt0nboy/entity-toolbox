<?php

/**
 * Class IdPropertyNotFieldable
 */
class IdPropertyNotFieldable extends IdProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_name'                => 'id',
        'default_schemas_fields_name' => array(
          'base'     => 'id',
          'revision' => 'id',
        ),
        'default_schemas_fields'      => array(
          'base'     => array(
            'description' => 'Primary Key: Unique %toolbox_info_entity_type% type identifier.',
          ),
        ),
      ),
      $args
    );

    parent::__construct($args);
  }
}