<?php

/**
 * Class TranslationIdProperty
 */
class TranslationIdProperty extends IntegerProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'default_type'                => 'entity_translation_id',
      'default_name'                => 't%toolbox_info_entity_type%_id',
      'default_label'               => 'Translation ID',
      'default_description'         => 'The translation ID for this the %toolbox_info_entity_type%.',
      'default_key'                 => 't%toolbox_info_entity_type%_id',
      'default_is_unique'           => FALSE,
      'default_has_revisions'       => FALSE,
      'default_schemas_fields_name' => array(
        'base'              => 't%toolbox_info_entity_type%_id',
        'revision'          => 't%toolbox_info_entity_type%_id',
        'relation'          => 't%toolbox_info_entity_type%_id',
        'relation_revision' => 't%toolbox_info_entity_type%_id',
      ),
      'default_schemas_fields'      => array(
        'base'              => array(
          'description' => 'The translation set id for this %toolbox_info_entity_type%, which equals the %toolbox_info_entity_type% id of the source in each set.',
          'type'        => 'int',
          'unsigned'    => TRUE,
          'not null'    => TRUE,
          'default'     => 0,
        ),
        'revision'          => NULL,
        'relation'          => array(
          'description' => 'The translation set id for this %toolbox_info_entity_type%, which equals the %toolbox_info_entity_type% id of the source in each set.',
          'type'        => 'int',
          'unsigned'    => TRUE,
          'not null'    => TRUE,
          'default'     => 0,
        ),
        'relation_revision' => NULL,
      ),
      'default_weight'              => 0
    ), $args);
    parent::__construct($args);
  }
}