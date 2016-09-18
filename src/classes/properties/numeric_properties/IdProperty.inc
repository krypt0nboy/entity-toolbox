<?php

/**
 * Class IdProperty
 */
class IdProperty extends IntegerProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'entity_id',
        'default_name'                => '%toolbox_info_entity_type%_id',
        'default_label'               => '%toolbox_info_labels_single% ID',
        'default_description'         => 'The %toolbox_info_labels_single% ID.',
        'default_key'                 => 'id',
        'default_required'            => TRUE,
        'default_is_unique'           => TRUE,
        'default_has_revisions'       => FALSE,
        'default_has_translations'    => FALSE,
        'default_schemas_fields_name' => array(
          'base'              => '%toolbox_info_entity_type%_id',
          'revision'          => '%toolbox_info_entity_type%_id',
          'relation'          => '%toolbox_info_entity_type%_id',
          'relation_revision' => '%toolbox_info_entity_type%_id',
        ),
        'default_schemas_fields'      => array(
          'base'              => array(
            'description' => 'Primary Key: Identifier for a %toolbox_info_entity_type%.',
            'type'        => 'serial',
            'unsigned'    => TRUE,
            'not null'    => TRUE,
          ),
          'revision'          => array(
            'description' => 'The {%toolbox_info_entity_type%}.%toolbox_info_entity_type%_id.',
            'unsigned'    => FALSE,
          ),
          'relation'          => array(
            'description' => 'The {%toolbox_info_entity_type%}.%toolbox_info_entity_type%_id.',
            'unsigned'    => FALSE,
          ),
          'relation_revision' => array(
            'description' => 'The {%toolbox_info_entity_type%}.%toolbox_info_entity_type%_id.',
            'unsigned'    => FALSE,
          ),
        ),
        'default_weight'              => -999
      ),
      $args
    );
    parent::__construct($args);
  }
}