<?php

/**
 * Class RevisionIdProperty
 */
class RevisionIdProperty extends IntegerProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'entity_revision_id',
        'default_name'                => 'revision',
        'default_label'               => 'Revision ID',
        'default_description'         => 'The unique ID of the %toolbox_info_entity_type% revision.',
        'default_key'                 => 'revision',
        'default_is_unique'           => FALSE,
        'default_has_revisions'       => FALSE,
        'default_has_translations'    => FALSE,
        'default_schemas_fields_name' => array(
          'base'              => 'vid',
          'revision'          => 'vid',
          'relation'          => 'vid',
          'relation_revision' => 'vid',
        ),
        'default_schemas_fields'      => array(
          'base'              => array(
            'description' => 'The current {%toolbox_info_tables_base%}.vid version identifier.',
            'type'        => 'int',
            'unsigned'    => TRUE,
            'not null'    => TRUE,
            'default'     => 0,
          ),
          'revision'          => array(
            'description' => 'The primary identifier for this version.',
            'type'        => 'serial',
            'not null'    => TRUE,
            'unsigned'    => TRUE,
            'default'     => 0,
          ),
          'relation'          => array(
            'description' => 'The current {%toolbox_info_tables_base%}.vid version identifier.',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
          ),
          'relation_revision' => array(
            'description' => 'The current {%toolbox_info_tables_base%}.vid version identifier.',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
          ),
        ),
        'default_weight'              => -998
      ),
      $args
    );
    parent::__construct($args);
  }
}